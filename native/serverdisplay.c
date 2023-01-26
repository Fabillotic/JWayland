#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-server-core.h>

jclass ServerDisplay_class;
jfieldID ServerDisplay_native_ptr;

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ServerDisplay_init_1jni(JNIEnv *env, jclass clazz) {
	ServerDisplay_class = clazz;
	ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ServerDisplay_create_1native(JNIEnv *env, jobject obj) {
	struct wl_display *display = wl_display_create();
	if(!display) {
		printf("FAILED TO CREATE DISPLAY!\n");
		fflush(stdout);
		return;
	}
	(*env)->SetLongField(env, obj, ServerDisplay_native_ptr, (jlong)(intptr_t)display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ServerDisplay_run(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_run(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ServerDisplay_terminate(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_terminate(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ServerDisplay_flush_1clients(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_flush_clients(display);
}

JNIEXPORT jstring JNICALL Java_dev_fabillo_jwayland_ServerDisplay_add_1socket_1auto(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return NULL;
	}

	return (*env)->NewStringUTF(env, wl_display_add_socket_auto(display));
}

JNIEXPORT jboolean JNICALL Java_dev_fabillo_jwayland_ServerDisplay_add_1socket_1fd(JNIEnv *env, jobject obj, jint fd) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return JNI_FALSE;
	}

	return wl_display_add_socket_fd(display, (int) fd) == 0 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_dev_fabillo_jwayland_ServerDisplay_add_1socket(JNIEnv *env, jobject obj, jstring name) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return JNI_FALSE;
	}

	return wl_display_add_socket(display, (*env)->GetStringUTFChars(env, name, NULL)) == 0 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ServerDisplay_destroy_1clients(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_destroy_clients(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ServerDisplay_destroy(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY DOES NOT EXIST!\n");
		fflush(stdout);
		return;
	}

	wl_display_destroy(display);
}
