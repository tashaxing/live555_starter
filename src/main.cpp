#include <iostream>
#include "stream_server.h"

#define MEDIA_SERVER_VERSION_STRING "1.10"

int main(int argc, char** argv)
{
    // Begin by setting up our usage environment:
    TaskScheduler* scheduler = BasicTaskScheduler::createNew();
    UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

    UserAuthenticationDatabase* authDB = NULL;
#ifdef ACCESS_CONTROL
    // To implement client access control to the RTSP server, do the following:
    authDB = new UserAuthenticationDatabase;
    authDB->addUserRecord("username1", "password1"); // replace these with real strings
    // Repeat the above with each <username>, <password> that you wish to allow
    // access to the server.
#endif

    // Create the RTSP server.  Try first with the default port number (554),
  // and then with the alternative port number (8554):
    RTSPServer* rtspServer;
    portNumBits rtspServerPortNum = 554;
    rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
    if (rtspServer == NULL) {
        rtspServerPortNum = 8554;
        rtspServer = DynamicRTSPServer::createNew(*env, rtspServerPortNum, authDB);
    }
    if (rtspServer == NULL) {
        std::cerr << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
        exit(1);
    }

    std::cout << "LIVE555 Media Server\n";
    std::cout << "\tversion " << MEDIA_SERVER_VERSION_STRING
        << " (LIVE555 Streaming Media library version "
        << LIVEMEDIA_LIBRARY_VERSION_STRING << ").\n";

    std::cout << "Play streams from this server using the URL\n";
    if (weHaveAnIPv4Address(*env)) {
        char* rtspURLPrefix = rtspServer->ipv4rtspURLPrefix();
        std::cout << "\t" << rtspURLPrefix << "<filename>\n";
        delete[] rtspURLPrefix;
        if (weHaveAnIPv6Address(*env)) *env << "or\n";
    }
    if (weHaveAnIPv6Address(*env)) {
        char* rtspURLPrefix = rtspServer->ipv6rtspURLPrefix();
        std::cout << "\t" << rtspURLPrefix << "<filename>\n";
        delete[] rtspURLPrefix;
    }
    std::cout << "where <filename> is a file present in the current directory, could be relative sub folder path.\n";

    std::cout << "Each file's type is inferred from its name suffix:\n";
    std::cout << "\t\".264\" => a H.264 Video Elementary Stream file\n";
    std::cout << "\t\".265\" => a H.265 Video Elementary Stream file\n";
    std::cout << "\t\".aac\" => an AAC Audio (ADTS format) file\n";
    std::cout << "\t\".ac3\" => an AC-3 Audio file\n";
    std::cout << "\t\".amr\" => an AMR Audio file\n";
    std::cout << "\t\".dv\" => a DV Video file\n";
    std::cout << "\t\".m4e\" => a MPEG-4 Video Elementary Stream file\n";
    std::cout << "\t\".mkv\" => a Matroska audio+video+(optional)subtitles file\n";
    std::cout << "\t\".mp3\" => a MPEG-1 or 2 Audio file\n";
    std::cout << "\t\".mpg\" => a MPEG-1 or 2 Program Stream (audio+video) file\n";
    std::cout << "\t\".ogg\" or \".ogv\" or \".opus\" => an Ogg audio and/or video file\n";
    std::cout << "\t\".ts\" => a MPEG Transport Stream file\n";
    std::cout << "\t\t(a \".tsx\" index file - if present - provides server 'trick play' support)\n";
    std::cout << "\t\".vob\" => a VOB (MPEG-2 video with AC-3 audio) file\n";
    std::cout << "\t\".wav\" => a WAV Audio file\n";
    std::cout << "\t\".webm\" => a WebM audio(Vorbis)+video(VP8) file\n";
    std::cout << "See http://www.live555.com/mediaServer/ for additional documentation.\n";

    // Also, attempt to create a HTTP server for RTSP-over-HTTP tunneling.
    // Try first with the default HTTP port (80), and then with the alternative HTTP
    // port numbers (8000 and 8080).

    if (rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8000) || rtspServer->setUpTunnelingOverHTTP(8080)) 
    {
        std::cout << "(We use port " << rtspServer->httpServerPortNum() << " for optional RTSP-over-HTTP tunneling).)\n";
    }
    else 
    {
        std::cout << "(RTSP-over-HTTP tunneling is not available.)\n";
    }

    // start server blocking this thread
    env->taskScheduler().doEventLoop(); // does not return

    return 0;
}