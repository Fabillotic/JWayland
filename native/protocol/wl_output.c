#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLOutput_release(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 0);
}

int wl_output_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLOutput$WLOutputListener");
	jmethodID mListener_geometry = (*env)->GetMethodID(env, listener_class, "geometry", "(IIIIILjava/lang/String;Ljava/lang/String;I)V");
	jmethodID mListener_mode = (*env)->GetMethodID(env, listener_class, "mode", "(IIII)V");
	jmethodID mListener_done = (*env)->GetMethodID(env, listener_class, "done", "()V");
	jmethodID mListener_scale = (*env)->GetMethodID(env, listener_class, "scale", "(I)V");
	jmethodID mListener_name = (*env)->GetMethodID(env, listener_class, "name", "(Ljava/lang/String;)V");
	jmethodID mListener_description = (*env)->GetMethodID(env, listener_class, "description", "(Ljava/lang/String;)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_geometry, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_mode, values); break;
		case 2: (*env)->CallVoidMethodA(env, listener, mListener_done, values); break;
		case 3: (*env)->CallVoidMethodA(env, listener, mListener_scale, values); break;
		case 4: (*env)->CallVoidMethodA(env, listener, mListener_name, values); break;
		case 5: (*env)->CallVoidMethodA(env, listener, mListener_description, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLOutput_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_output_dispatcher, listener_ref, data);
}
