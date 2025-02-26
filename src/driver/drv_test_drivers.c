#include "../new_common.h"
#include "../cmnds/cmd_public.h"
#include "../logging/logging.h"
#include "drv_local.h"

static float base_v = 120;
static float base_c = 1;
static float base_p = 120;
static bool bAllowRandom = true;

commandResult_t TestPower_Setup(const void* context, const char* cmd, const char* args, int cmdFlags) {
	

	Tokenizer_TokenizeString(args, TOKENIZER_ALLOW_QUOTES | TOKENIZER_DONT_EXPAND);
	if (Tokenizer_GetArgsCount() < 3) {
		ADDLOG_INFO(LOG_FEATURE_ENERGYMETER, "TestPower_Setup: command require at least 4 args");
		return CMD_RES_NOT_ENOUGH_ARGUMENTS;
	}
	base_v = Tokenizer_GetArgFloat(0);
	base_c = Tokenizer_GetArgFloat(1);
	base_p = Tokenizer_GetArgFloat(2);
	bAllowRandom = Tokenizer_GetArgInteger(3);


	return CMD_RES_OK;
}
//Test Power driver
void Test_Power_Init() {
	BL_Shared_Init();

	//cmddetail:{"name":"SetupTestPower","args":"",
	//cmddetail:"descr":"NULL",
	//cmddetail:"fn":"TestPower_Setup","file":"driver/drv_test_drivers.c","requires":"",
	//cmddetail:"examples":""}
	CMD_RegisterCommand("SetupTestPower", "", TestPower_Setup, NULL, NULL);
}
void Test_Power_RunFrame() {
	float final_v = base_v;
	float final_c = base_c;
	float final_p = base_p;

	if (bAllowRandom) {
		final_c += (rand() % 100) * 0.001f;
		final_v += (rand() % 100) * 0.1f;
		final_p += (rand() % 100) * 0.1f;
	}
	BL_ProcessUpdate(final_v, final_c, final_p);
}

//Test LED driver
void Test_LED_Driver_Init() {
}
void Test_LED_Driver_RunFrame() {
}
void Test_LED_Driver_OnChannelChanged(int ch, int value) {
}