#ifndef _DENNIS_THINK_C_UDP_CLIENT_H_
#define _DENNIS_THINK_C_UDP_CLIENT_H_
#include "CommonMsg.h"
#include "asio_common.h"
#include "Log.h"
#include <memory>
namespace ClientCore {
	class CUdpClient : public std::enable_shared_from_this<CUdpClient>
	{
	public:
		CUdpClient(asio::io_context& ioService, const std::string strIp, const int port);
		void StartConnect();
		void SendKeepAlive();
		void send_msg(const asio::ip::udp::endpoint endPt, TransBaseMsg_t* pMsg);
		void send_msg(const std::string strIp, const int port, const BaseMsg* pMsg);
		void sendToServer(TransBaseMsg_t* pMsg);
	public:
		static std::shared_ptr<spdlog::logger> ms_loger;
	private:
		std::string m_udpServerIp;
		int m_udpServerPort;
		asio::ip::udp::endpoint m_udpServerPt;
		asio::ip::udp::endpoint m_clientPt;
		asio::ip::udp::endpoint m_recvFromPt;
		std::shared_ptr<asio::ip::udp::socket> m_udpSocket;
		void do_read();
		std::string EndPoint(const asio::ip::udp::endpoint endPt);
		void handle_msg(const asio::ip::udp::endpoint endPt, TransBaseMsg_t* pMsg);
	
		static const int max_msg_length_udp = 8092;
		char m_sendbuf[max_msg_length_udp];
		char m_recvbuf[max_msg_length_udp];
	};
}
#endif