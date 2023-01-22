#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

int wlcallback_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	free(user_data);
	printf("CALLBACK DISPATCHER! opcode: %d, name: '%s', signature: '%s', target: %p\n", opcode, msg->name, msg->signature, target);
	fflush(stdout);
	jobject listener = (jobject) implementation;

	jclass WLCallbackListener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLCallback$WLCallbackListener");
	jmethodID WLCallbackListener_done = (*env)->GetMethodID(env, WLCallbackListener_class, "done", "(I)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);

	printf("Values: %p\n", values);
	fflush(stdout);

	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, WLCallbackListener_done, values); break;
		default:
			printf("ERROR! DISPATCHER CALLED ON INVALID OPCODE!!!!!!!\n");
			fflush(stdout);
			break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLCallback_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *proxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv** data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(proxy, wlcallback_dispatcher, listener_ref, data);
}
