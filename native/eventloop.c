#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-server-core.h>

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_WLEventLoop_dispatch(JNIEnv *env, jobject obj, jint timeout) {
	jclass WLEventLoop_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLEventLoop");
	jfieldID WLEventLoop_native_ptr = (*env)->GetFieldID(env, WLEventLoop_class, "native_ptr", "J");

	struct wl_event_loop *wloop = (struct wl_event_loop*)(intptr_t)(*env)->GetLongField(env, obj, WLEventLoop_native_ptr);
	wl_event_loop_dispatch(wloop, (int) timeout);
}
