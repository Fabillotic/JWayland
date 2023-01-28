#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wayland-server-core.h>
#include "interfaces.h"

jclass ServerDisplay_class;
jfieldID ServerDisplay_native_ptr;

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_init_1jni(JNIEnv *env, jclass clazz) {
	ServerDisplay_class = clazz;
	ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_create_1native(JNIEnv *env, jobject obj) {
	struct wl_display *display = wl_display_create();
	if(!display) {
		printf("FAILED TO CREATE DISPLAY!\n");
		fflush(stdout);
		return;
	}
	(*env)->SetLongField(env, obj, ServerDisplay_native_ptr, (jlong)(intptr_t)display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_run(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_run(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_terminate(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_terminate(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_flush_1clients(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_flush_clients(display);
}

JNIEXPORT jstring JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_add_1socket_1auto(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return NULL;
	}

	return (*env)->NewStringUTF(env, wl_display_add_socket_auto(display));
}

JNIEXPORT jboolean JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_add_1socket_1fd(JNIEnv *env, jobject obj, jint fd) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return JNI_FALSE;
	}

	return wl_display_add_socket_fd(display, (int) fd) == 0 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_add_1socket(JNIEnv *env, jobject obj, jstring name) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return JNI_FALSE;
	}

	return wl_display_add_socket(display, (*env)->GetStringUTFChars(env, name, NULL)) == 0 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_destroy_1clients(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_destroy_clients(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_destroy(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_destroy(display);
}

struct global_data {
	JNIEnv *env;
	jobject listener;
};

void global_bind(struct wl_client *client, void *data, uint32_t version, uint32_t id) {
	struct global_data *d = (struct global_data*) data;
	JNIEnv *env = d->env;

	jclass WLGlobalBindListener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLGlobal$WLGlobalBindListener");
	//jmethodID WLGlobalBindListener_bind = (*env)->GetMethodID(env, WLGlobalBindListener_class, "bind", "(Ldev/fabillo/jwayland/server/WLClient;II)V");
	jmethodID WLGlobalBindListener_bind = (*env)->GetMethodID(env, WLGlobalBindListener_class, "bind", "(JII)V");

	(*env)->CallVoidMethod(env, d->listener, WLGlobalBindListener_bind, (jlong)(intptr_t)client, (jint)version, (jint)id);
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_create_1global(JNIEnv *env, jobject obj, jstring interface_name, jint version, jobject listener) {
	jclass WLGlobal_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLGlobal");
	jfieldID WLGlobal_native_ptr = (*env)->GetFieldID(env, WLGlobal_class, "native_ptr", "J");
	jmethodID WLGlobal_init = (*env)->GetMethodID(env, WLGlobal_class, "<init>", "()V");

	struct wl_display *display;
	struct global_data *data;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return NULL;
	}
	jobject listener_ref = (*env)->NewGlobalRef(env, listener);
	data = malloc(sizeof(struct global_data));
	data->env = env;
	data->listener = listener_ref;

	struct wl_global *glob = wl_global_create(display, get_interface_by_name((*env)->GetStringUTFChars(env, interface_name, NULL)), (int) version, data, global_bind);
	if(!glob) return NULL;

	jobject global = (*env)->NewObject(env, WLGlobal_class, WLGlobal_init);
	(*env)->SetLongField(env, global, WLGlobal_native_ptr, (jlong)(intptr_t)glob);
	return global;
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_create_1resource(JNIEnv *env, jobject obj, jlong client, jstring interface_name, jint version, jint id) {
	jclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");
	jfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");
	jmethodID WLResource_init = (*env)->GetMethodID(env, WLResource_class, "<init>", "()V");

	struct wl_client *cl = (struct wl_client*)(intptr_t)client;

	const struct wl_interface *inf = get_interface_by_name((*env)->GetStringUTFChars(env, interface_name, NULL));
	if(!inf) return NULL;

	struct wl_resource *r = wl_resource_create(cl, inf, (int) version, (uint32_t) id);
	if(!r) return NULL;

	jobject resource = (*env)->NewObject(env, WLResource_class, WLResource_init);
	(*env)->SetLongField(env, resource, WLResource_native_ptr, (jlong)(intptr_t)r);
	return resource;
}
