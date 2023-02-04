#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-server-core.h>

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_WLResource_get_1client(JNIEnv *env, jobject obj) {
	jclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");
	jfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");
	jclass WLClient_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLClient");
	jfieldID WLClient_native_ptr = (*env)->GetFieldID(env, WLClient_class, "native_ptr", "J");
	jmethodID WLClient_init = (*env)->GetMethodID(env, WLClient_class, "<init>", "()V");

	struct wl_resource *resource = (struct wl_resource*)(intptr_t)(*env)->GetLongField(env, obj, WLResource_native_ptr);

	struct wl_client *c = wl_resource_get_client(resource);

	jobject client = (*env)->NewObject(env, WLClient_class, WLClient_init);
	(*env)->SetLongField(env, client, WLClient_native_ptr, (jlong)(intptr_t)c);
	return client;
}
