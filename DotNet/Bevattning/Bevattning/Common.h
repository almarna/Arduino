#ifndef _COMMON_h
#define _COMMON_h

class DeviceStatus
{
public:
	int Code;
	char Message[50];

	DeviceStatus(int newCode, char* newMessage)
	{
		Code = newCode;
		strcpy(Message, newMessage);
	}
};

#endif
