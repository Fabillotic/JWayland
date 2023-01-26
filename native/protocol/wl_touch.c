#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLTouch_release(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 0);
}

int wl_touch_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLTouch$WLTouchListener");
	jmethodID mListener_down = (*env)->GetMethodID(env, listener_class, "down", "(IILdev/fabillo/jwayland/WLProxy;III)V");
	jmethodID mListener_up = (*env)->GetMethodID(env, listener_class, "up", "(III)V");
	jmethodID mListener_motion = (*env)->GetMethodID(env, listener_class, "motion", "(IIII)V");
	jmethodID mListener_frame = (*env)->GetMethodID(env, listener_class, "frame", "()V");
	jmethodID mListener_cancel = (*env)->GetMethodID(env, listener_class, "cancel", "()V");
	jmethodID mListener_shape = (*env)->GetMethodID(env, listener_class, "shape", "(III)V");
	jmethodID mListener_orientation = (*env)->GetMethodID(env, listener_class, "orientation", "(II)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_down, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_up, values); break;
		case 2: (*env)->CallVoidMethodA(env, listener, mListener_motion, values); break;
		case 3: (*env)->CallVoidMethodA(env, listener, mListener_frame, values); break;
		case 4: (*env)->CallVoidMethodA(env, listener, mListener_cancel, values); break;
		case 5: (*env)->CallVoidMethodA(env, listener, mListener_shape, values); break;
		case 6: (*env)->CallVoidMethodA(env, listener, mListener_orientation, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLTouch_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_touch_dispatcher, listener_ref, data);
}
