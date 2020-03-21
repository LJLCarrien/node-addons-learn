#include <stdio.h>
#include <node_api.h>
#include <string.h>

napi_value Hello(napi_env env, napi_callback_info info) {
	size_t argc = 1;         // ֻ����һ������
	napi_value argv;         // ���յ��Ĳ���
	char n[40];
	char hello[90] = "Hello ";
	napi_value result;
	napi_get_cb_info(env, info, &argc, &argv, NULL, NULL);                     // ��ȡ���ղ���
	napi_get_value_string_utf8(env, argv, n, sizeof(n), NULL);                 // �����յ��Ĳ���ת��Ϊ C ��������
	napi_create_string_utf8(env, strcat(hello, n), NAPI_AUTO_LENGTH, &result); // ƴ���ַ���

	return result;
}

napi_value Init(napi_env env, napi_value exports) {
	// ���� hello ����
	napi_property_descriptor desc = {
		"hello",
		NULL,
		Hello,
		NULL,
		NULL,
		NULL,
		napi_default,
		NULL };
	// �� hello ���ص� exports ���� === require('hello.node').hello;
	napi_define_properties(env, exports, 1, &desc);

	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
