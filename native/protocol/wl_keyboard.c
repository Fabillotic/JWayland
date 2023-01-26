#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLKeyboard_release(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 0);
}

int wl_keyboard_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLKeyboard$WLKeyboardListener");
	jmethodID mListener_keymap = (*env)->GetMethodID(env, listener_class, "keymap", "(III)V");
	jmethodID mListener_enter = (*env)->GetMethodID(env, listener_class, "enter", "(ILdev/fabillo/jwayland/WLProxy;J)V");
	jmethodID mListener_leave = (*env)->GetMethodID(env, listener_class, "leave", "(ILdev/fabillo/jwayland/WLProxy;)V");
	jmethodID mListener_key = (*env)->GetMethodID(env, listener_class, "key", "(IIII)V");
	jmethodID mListener_modifiers = (*env)->GetMethodID(env, listener_class, "modifiers", "(IIIII)V");
	jmethodID mListener_repeat_info = (*env)->GetMethodID(env, listener_class, "repeat_info", "(II)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_keymap, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_enter, values); break;
		case 2: (*env)->CallVoidMethodA(env, listener, mListener_leave, values); break;
		case 3: (*env)->CallVoidMethodA(env, listener, mListener_key, values); break;
		case 4: (*env)->CallVoidMethodA(env, listener, mListener_modifiers, values); break;
		case 5: (*env)->CallVoidMethodA(env, listener, mListener_repeat_info, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLKeyboard_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_keyboard_dispatcher, listener_ref, data);
}
