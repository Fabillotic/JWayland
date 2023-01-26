#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_pong(JNIEnv *env, jobject obj, jint serial) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 0, (uint32_t) serial);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_move(JNIEnv *env, jobject obj, jobject seat, jint serial) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 1, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, seat, WLProxy_native_ptr), (uint32_t) serial);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_resize(JNIEnv *env, jobject obj, jobject seat, jint serial, jint edges) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 2, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, seat, WLProxy_native_ptr), (uint32_t) serial, (uint32_t) edges);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_set_1toplevel(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 3);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_set_1transient(JNIEnv *env, jobject obj, jobject parent, jint x, jint y, jint flags) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 4, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, parent, WLProxy_native_ptr), (int32_t) x, (int32_t) y, (uint32_t) flags);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_set_1fullscreen(JNIEnv *env, jobject obj, jint method, jint framerate, jobject output) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 5, (uint32_t) method, (uint32_t) framerate, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, output, WLProxy_native_ptr));
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_set_1popup(JNIEnv *env, jobject obj, jobject seat, jint serial, jobject parent, jint x, jint y, jint flags) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 6, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, seat, WLProxy_native_ptr), (uint32_t) serial, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, parent, WLProxy_native_ptr), (int32_t) x, (int32_t) y, (uint32_t) flags);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_set_1maximized(JNIEnv *env, jobject obj, jobject output) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 7, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, output, WLProxy_native_ptr));
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_set_1title(JNIEnv *env, jobject obj, jstring title) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 8, (*env)->GetStringUTFChars(env, title, NULL));
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_set_1class(JNIEnv *env, jobject obj, jstring class_) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 9, (*env)->GetStringUTFChars(env, class_, NULL));
}

int wl_shell_surface_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLShellSurface$WLShellSurfaceListener");
	jmethodID mListener_ping = (*env)->GetMethodID(env, listener_class, "ping", "(I)V");
	jmethodID mListener_configure = (*env)->GetMethodID(env, listener_class, "configure", "(III)V");
	jmethodID mListener_popup_done = (*env)->GetMethodID(env, listener_class, "popup_done", "()V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_ping, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_configure, values); break;
		case 2: (*env)->CallVoidMethodA(env, listener, mListener_popup_done, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShellSurface_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_shell_surface_dispatcher, listener_ref, data);
}
