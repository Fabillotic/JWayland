#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static inline void arguments_to_java(JNIEnv *env, const struct wl_message *msg, union wl_argument *args, char **r_sig, jvalue **r_values) {
	int i, n;
	char c;
	char *sig;
	jvalue *values;

	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	sig = malloc(200);
	sig[0] = '\0';
	for(i = 0; (c = msg->signature[i]) != '\0'; i++) {
		printf("Character: %c\n", c);
		fflush(stdout);
		if(c >= '0' && c <= '9') continue;
		else if(c == '?') continue;
		else if(c == 'i' || c == 'u' || c == 'h' || c == 'f' || c == 'n') {
			printf("FOUND NUMBER!!\n");
			fflush(stdout);
			strcat(sig, "I");
			n++;
		}
		else if(c == 's') {
			strcat(sig, "Ljava/lang/String;");
			n++;
		}
		else if(c == 'o') {
			strcat(sig, "Ldev/fabillo/jwayland/WLProxy;");
			n++;
		}
		else if(c == 'a') {
			/* TODO: Not yet supported */
		}
	}
	if(n > 0) {
		values = malloc(sizeof(jvalue) * n);
		n = 0;
		for(i = 0; (c = msg->signature[i]) != '\0'; i++) {
			if(c >= '0' && c <= '9') continue;
			else if(c == '?') continue;
			else if(c == 'i' || c == 'u' || c == 'h' || c == 'f' || c == 'n') {
				values[n].i = (jint) args[n].i;
				n++;
			}
			else if(c == 's') {
				values[n].l = (jobject) (*env)->NewStringUTF(env, args[n].s);
				n++;
			}
			else if(c == 'o') {
				values[n].l = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
				(*env)->SetLongField(env, values[n].l, WLProxy_native_ptr, (jlong)(intptr_t)args[n].o);
				n++;
			}
		}
		*r_values = values;
	}
	else *r_values = NULL;
	*r_sig = sig;
}
