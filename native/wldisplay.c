#include <jni.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLDisplay_addListener(JNIEnv *env, jobject obj, jobject listener) {
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_protocol_WLDisplay_sync(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	union wl_argument args[1];
	args[0].n = 0;
	struct wl_proxy *nproxy = wl_proxy_marshal_array_constructor(wproxy, 0, args, get_interface_by_name("wl_callback"));
	jobject prox = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
	(*env)->SetLongField(env, prox, WLProxy_native_ptr, (jlong)(intptr_t)nproxy);
	return prox;
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_protocol_WLDisplay_get_1registry(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	struct wl_proxy *proxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	union wl_argument args[1];
	args[0].n = 0;
	struct wl_proxy *nproxy = wl_proxy_marshal_array_constructor(proxy, 1, args, get_interface_by_name("wl_registry"));
	jobject prox = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
	(*env)->SetLongField(env, prox, WLProxy_native_ptr, (jlong)(intptr_t)nproxy);
	return prox;
}
