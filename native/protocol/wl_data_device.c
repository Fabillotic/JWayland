#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDataDevice_start_1drag(JNIEnv *env, jobject obj, jobject source, jobject origin, jobject icon, jint serial) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 0, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, source, WLProxy_native_ptr), (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, origin, WLProxy_native_ptr), (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, icon, WLProxy_native_ptr), (uint32_t) serial);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDataDevice_set_1selection(JNIEnv *env, jobject obj, jobject source, jint serial) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 1, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, source, WLProxy_native_ptr), (uint32_t) serial);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDataDevice_release(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 2);
}

int wl_data_device_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLDataDevice$WLDataDeviceListener");
	jmethodID mListener_data_offer = (*env)->GetMethodID(env, listener_class, "data_offer", "(Ldev/fabillo/jwayland/WLProxy;)V");
	jmethodID mListener_enter = (*env)->GetMethodID(env, listener_class, "enter", "(ILdev/fabillo/jwayland/WLProxy;IILdev/fabillo/jwayland/WLProxy;)V");
	jmethodID mListener_leave = (*env)->GetMethodID(env, listener_class, "leave", "()V");
	jmethodID mListener_motion = (*env)->GetMethodID(env, listener_class, "motion", "(III)V");
	jmethodID mListener_drop = (*env)->GetMethodID(env, listener_class, "drop", "()V");
	jmethodID mListener_selection = (*env)->GetMethodID(env, listener_class, "selection", "(Ldev/fabillo/jwayland/WLProxy;)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_data_offer, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_enter, values); break;
		case 2: (*env)->CallVoidMethodA(env, listener, mListener_leave, values); break;
		case 3: (*env)->CallVoidMethodA(env, listener, mListener_motion, values); break;
		case 4: (*env)->CallVoidMethodA(env, listener, mListener_drop, values); break;
		case 5: (*env)->CallVoidMethodA(env, listener, mListener_selection, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDataDevice_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_data_device_dispatcher, listener_ref, data);
}
