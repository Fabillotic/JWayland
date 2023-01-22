#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WPSinglePixelBufferManagerV1_destroy(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	union wl_argument args[0];
	struct wl_proxy *nproxy;
	wl_proxy_marshal_array(wproxy, 0, args);
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_protocol_WPSinglePixelBufferManagerV1_create_1u32_1rgba_1buffer(JNIEnv *env, jobject obj, jint r, jint g, jint b, jint a) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	union wl_argument args[4];
	args[0].u = (uint32_t) r;
	args[1].u = (uint32_t) g;
	args[2].u = (uint32_t) b;
	args[3].u = (uint32_t) a;
	struct wl_interface *inf = get_interface_by_name("wl_buffer");
	struct wl_proxy *nproxy;
	if(inf) {
		nproxy = wl_proxy_marshal_array_constructor(wproxy, 1, args, inf);
		if(nproxy) {
			jobject prox = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
			(*env)->SetLongField(env, prox, WLProxy_native_ptr, (jlong)(intptr_t)nproxy);
			return prox;
		}
		else return NULL;
	}
	return NULL;
}
