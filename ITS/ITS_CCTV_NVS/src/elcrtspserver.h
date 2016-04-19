#include <liveMedia.hh>
#include <UsageEnvironment.hh>
#include <BasicUsageEnvironment.hh>
#include <Groupsock.hh>
#include <string>
#include <vector>

class ELCRTSPServer :public RTSPServer
{
public:

	//overide function
	virtual RTSPServer::RTSPClientConnection*	  createNewClientConnection(int clientSocket, struct sockaddr_in clientAddr);
	virtual RTSPServer::RTSPClientSession*	createNewClientSession(u_int32_t sessionId);

	static ELCRTSPServer* createNew(UsageEnvironment& env, Port ourPort = 554,
								   UserAuthenticationDatabase* authDatabase = NULL,
								   unsigned reclamationTestSeconds = 65);

	ELCRTSPServer(UsageEnvironment& env,
				 int ourSocket, Port ourPort,
				 UserAuthenticationDatabase* authDatabase,
				 unsigned reclamationTestSeconds);
	virtual ~ELCRTSPServer();

	static std::vector<std::string> getFileDirectory(std::string ID,std::string ts, std::string te, int &codec);
	static std::string getOldestItem(std::string path);

public:
	//NvrRTSPClientConnection
	class NvrRTSPClientConnection : public RTSPServer::RTSPClientConnection
	{
		public:
			NvrRTSPClientConnection(RTSPServer& ourServer, int clientSocket, struct sockaddr_in clientAddr);
			virtual ~NvrRTSPClientConnection();
			char* getBufferRespond();

		protected:
			virtual void handleCmd_DESCRIBE(char const* urlPreSuffix, char const* urlSuffix, char const* fullRequestStr);
	};//end class NvrRTSPClientConnection


	//NvrRTSPClientSession
	class NvrRTSPClientSession : public RTSPServer::RTSPClientSession
	{
		public:
			NvrRTSPClientSession(RTSPServer& ourServer, u_int32_t sessionId);
			virtual ~NvrRTSPClientSession();

		protected:
			virtual void handleCmd_SETUP(RTSPServer::RTSPClientConnection* ourClientConnection,
										 char const* urlPreSuffix, char const* urlSuffix, char const* fullRequestStr);
			virtual void handleCmd_TEARDOWN(RTSPServer::RTSPClientConnection* ourClientConnection,
											ServerMediaSubsession* subsession);
			virtual void handleCmd_PLAY(RTSPServer::RTSPClientConnection* ourClientConnection,
										ServerMediaSubsession* subsession, char const* fullRequestStr);
			virtual void handleCmd_PAUSE(RTSPServer::RTSPClientConnection* ourClientConnection,
										 ServerMediaSubsession* subsession);
	};//end class NvrRTSPClientSession



};
