#pragma once

#include "checksum_crc.h"

typedef struct player_info_s
{
	char name[MAX_PLAYER_NAME_LENGTH];
	int userID;
	char guid[SIGNED_GUID_LEN + 1];
	uint32 friendsID;
	char friendsName[MAX_PLAYER_NAME_LENGTH];
	bool fakeplayer;
	bool ishltv;
	bool isreplay;
	CRC32_t customFiles[MAX_CUSTOM_FILES];
	unsigned char filesDownloaded;
} player_info_t;