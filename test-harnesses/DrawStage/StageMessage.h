/**
 * @brief Stage Message
 */

#ifndef STAGEMESSAGE_H
#define STAGEMESSAGE_H 1

#define STAGE_CMD_SET 0
#define STAGE_CMD_DISPLAY 1
#define STAGE_CMD_STOP 2

struct StageMessage
{
	struct Message msg;
	int cmd;
	int playerNo;
	int stageNo;
};

#endif /* STAGEMESSAGE_H */
