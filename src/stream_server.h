#ifndef _STREAM_SERVER_H_
#define _STREAM_SERVER_H_

#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"
#include "RTSPServer.hh"

class DynamicRTSPServer: public RTSPServer 
{
public:
  static DynamicRTSPServer* createNew(UsageEnvironment& env, Port ourPort,
                      UserAuthenticationDatabase* authDatabase,
                      unsigned reclamationTestSeconds = 65);

protected:
  DynamicRTSPServer(UsageEnvironment& env, int ourSocketIPv4, int ourSocketIPv6, Port ourPort,
            UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds);
  // called only by createNew();
  virtual ~DynamicRTSPServer();

protected: // redefined virtual functions
  virtual void lookupServerMediaSession(char const* streamName,
                    lookupServerMediaSessionCompletionFunc* completionFunc,
                    void* completionClientData,
                    Boolean isFirstLookupInSession);
};

#endif