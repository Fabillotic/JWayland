#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLPointer_set_1cursor(JNIEnv *env, jobject obj, jint serial, jobject surface, jint hotspot_x, jint hotspot_y) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 0, (uint32_t) serial, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, surface, WLProxy_native_ptr), (int32_t) hotspot_x, (int32_t) hotspot_y);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLPointer_release(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 1);
}

int wl_pointer_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLPointer$WLPointerListener");
	jmethodID mListener_enter = (*env)->GetMethodID(env, listener_class, "enter", "(ILdev/fabillo/jwayland/WLProxy;II)V");
	jmethodID mListener_leave = (*env)->GetMethodID(env, listener_class, "leave", "(ILdev/fabillo/jwayland/WLProxy;)V");
	jmethodID mListener_motion = (*env)->GetMethodID(env, listener_class, "motion", "(III)V");
	jmethodID mListener_button = (*env)->GetMethodID(env, listener_class, "button", "(IIII)V");
	jmethodID mListener_axis = (*env)->GetMethodID(env, listener_class, "axis", "(III)V");
	jmethodID mListener_frame = (*env)->GetMethodID(env, listener_class, "frame", "()V");
	jmethodID mListener_axis_source = (*env)->GetMethodID(env, listener_class, "axis_source", "(I)V");
	jmethodID mListener_axis_stop = (*env)->GetMethodID(env, listener_class, "axis_stop", "(II)V");
	jmethodID mListener_axis_discrete = (*env)->GetMethodID(env, listener_class, "axis_discrete", "(II)V");
	jmethodID mListener_axis_value120 = (*env)->GetMethodID(env, listener_class, "axis_value120", "(II)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_enter, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_leave, values); break;
		case 2: (*env)->CallVoidMethodA(env, listener, mListener_motion, values); break;
		case 3: (*env)->CallVoidMethodA(env, listener, mListener_button, values); break;
		case 4: (*env)->CallVoidMethodA(env, listener, mListener_axis, values); break;
		case 5: (*env)->CallVoidMethodA(env, listener, mListener_frame, values); break;
		case 6: (*env)->CallVoidMethodA(env, listener, mListener_axis_source, values); break;
		case 7: (*env)->CallVoidMethodA(env, listener, mListener_axis_stop, values); break;
		case 8: (*env)->CallVoidMethodA(env, listener, mListener_axis_discrete, values); break;
		case 9: (*env)->CallVoidMethodA(env, listener, mListener_axis_value120, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLPointer_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_pointer_dispatcher, listener_ref, data);
}
