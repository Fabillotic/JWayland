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
	wl_global_create(display, get_interface_by_name((*env)->GetStringUTFChars(env, interface_name, NULL)), (int) version, data, global_bind);
	return NULL;
}
