#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDataSource_offer(JNIEnv *env, jobject obj, jstring mime_type) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 0, (*env)->GetStringUTFChars(env, mime_type, NULL));
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDataSource_destroy(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 1);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDataSource_set_1actions(JNIEnv *env, jobject obj, jint dnd_actions) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 2, (uint32_t) dnd_actions);
}

int wl_data_source_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLDataSource$WLDataSourceListener");
	jmethodID mListener_target = (*env)->GetMethodID(env, listener_class, "target", "(Ljava/lang/String;)V");
	jmethodID mListener_send = (*env)->GetMethodID(env, listener_class, "send", "(Ljava/lang/String;I)V");
	jmethodID mListener_cancelled = (*env)->GetMethodID(env, listener_class, "cancelled", "()V");
	jmethodID mListener_dnd_drop_performed = (*env)->GetMethodID(env, listener_class, "dnd_drop_performed", "()V");
	jmethodID mListener_dnd_finished = (*env)->GetMethodID(env, listener_class, "dnd_finished", "()V");
	jmethodID mListener_action = (*env)->GetMethodID(env, listener_class, "action", "(I)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_target, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_send, values); break;
		case 2: (*env)->CallVoidMethodA(env, listener, mListener_cancelled, values); break;
		case 3: (*env)->CallVoidMethodA(env, listener, mListener_dnd_drop_performed, values); break;
		case 4: (*env)->CallVoidMethodA(env, listener, mListener_dnd_finished, values); break;
		case 5: (*env)->CallVoidMethodA(env, listener, mListener_action, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDataSource_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_data_source_dispatcher, listener_ref, data);
}
