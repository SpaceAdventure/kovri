#ifndef STREAMING_H__
#define STREAMING_H__

#include <inttypes.h>
#include <map>
#include "LeaseSet.h"
#include "I2NPProtocol.h"

namespace i2p
{
namespace stream
{
	const uint16_t PACKET_FLAG_SYNCHRONIZE = 0x0001;
	const uint16_t PACKET_FLAG_CLOSE = 0x0002;
	const uint16_t PACKET_FLAG_RESET = 0x0004;
	const uint16_t PACKET_FLAG_SIGNATURE_INCLUDED = 0x0008;
	const uint16_t PACKET_FLAG_SIGNATURE_REQUESTED = 0x0010;
	const uint16_t PACKET_FLAG_FROM_INCLUDED = 0x0020;
	const uint16_t PACKET_FLAG_DELAY_REQUESTED = 0x0040;
	const uint16_t PACKET_FLAG_MAX_PACKET_SIZE_INCLUDED = 0x0080;
	const uint16_t PACKET_FLAG_PROFILE_INTERACTIVE = 0x0100;
	const uint16_t PACKET_FLAG_ECHO = 0x0200;
	const uint16_t PACKET_FLAG_NO_ACK = 0x0400;

	class Stream
	{	
		public:

			Stream (const i2p::data::IdentHash& destination);
			uint32_t GetSendStreamID () const { return m_SendStreamID; };
			uint32_t GetRecvStreamID () const { return m_RecvStreamID; };

			void HandleNextPacket (const uint8_t * buf, size_t len);
			
		private:

			uint32_t m_SendStreamID, m_RecvStreamID;
	};
	
	class StreamingDestination
	{
		public:

			Stream * CreateNewStream (const i2p::data::IdentHash& destination);
			void HandleNextPacket (const uint8_t * buf, size_t len);

		private:

			std::map<uint32_t, Stream *> m_Streams;
	};	
	
	// assuming data is I2CP message
	void HandleDataMessage (i2p::data::IdentHash * destination, const uint8_t * buf, size_t len);
	I2NPMessage * CreateDataMessage (Stream * s, uint8_t * payload, size_t len);
}		
}	

#endif