#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wayland-util.h>

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_WLArray_init(JNIEnv *env, jclass clazz) {
	jclass WLArray_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLArray");
	jfieldID WLArray_native_ptr = (*env)->GetFieldID(env, WLArray_class, "native_ptr", "J");
	jmethodID WLArray_init = (*env)->GetMethodID(env, WLArray_class, "<init>", "()V");

	struct wl_array *warray = malloc(sizeof(struct wl_array));
	wl_array_init(warray);

	jobject array = (*env)->NewObject(env, WLArray_class, WLArray_init);
	(*env)->SetLongField(env, array, WLArray_native_ptr, (jlong)(intptr_t)warray);
	return array;
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_WLArray_getData(JNIEnv *env, jobject obj) {
	jclass WLArray_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLArray");
	jfieldID WLArray_native_ptr = (*env)->GetFieldID(env, WLArray_class, "native_ptr", "J");

	struct wl_array *array = (struct wl_array*)(intptr_t)(*env)->GetLongField(env, obj, WLArray_native_ptr);

	return (*env)->NewDirectByteBuffer(env, array->data, (jlong)array->size);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_WLArray_release(JNIEnv *env, jobject obj) {
	jclass WLArray_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLArray");
	jfieldID WLArray_native_ptr = (*env)->GetFieldID(env, WLArray_class, "native_ptr", "J");

	struct wl_array *array = (struct wl_array*)(intptr_t)(*env)->GetLongField(env, obj, WLArray_native_ptr);

	wl_array_release(array);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_WLArray_add(JNIEnv *env, jobject obj, jint bytes) {
	jclass WLArray_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLArray");
	jfieldID WLArray_native_ptr = (*env)->GetFieldID(env, WLArray_class, "native_ptr", "J");

	struct wl_array *array = (struct wl_array*)(intptr_t)(*env)->GetLongField(env, obj, WLArray_native_ptr);

	wl_array_add(array, (size_t)bytes);
}
