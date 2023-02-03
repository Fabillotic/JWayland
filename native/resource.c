#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-server-core.h>

JNIEXPORT jlong JNICALL Java_dev_fabillo_jwayland_server_WLResource_get_1client(JNIEnv *env, jobject obj) {
	jclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");
	jfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");

	struct wl_resource *resource = (struct wl_resource*)(intptr_t)(*env)->GetLongField(env, obj, WLResource_native_ptr);
	return (jlong)(intptr_t)wl_resource_get_client(resource);
}
