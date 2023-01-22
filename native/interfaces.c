#include <stddef.h>
#include <wayland-client-core.h>
#include "interfaces.h"

/* wl_display */
struct wl_message wl_display_requests[] = {
	{"sync", "n", (struct wl_interface*[]) {&wl_callback_interface}},
	{"get_registry", "n", (struct wl_interface*[]) {&wl_registry_interface}}
};

struct wl_message wl_display_events[] = {
	{"error", "ous", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"delete_id", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_display_interface = {
	"wl_display", 1,
	2, wl_display_requests,
	2, wl_display_events
};

/* wl_callback */
struct wl_message wl_callback_requests[] = {
};

struct wl_message wl_callback_events[] = {
	{"done", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_callback_interface = {
	"wl_callback", 1,
	0, wl_callback_requests,
	1, wl_callback_events
};

/* wl_registry */
struct wl_message wl_registry_requests[] = {
	{"bind", "usun", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}}
};

struct wl_message wl_registry_events[] = {
	{"global", "usu", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"global_remove", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_registry_interface = {
	"wl_registry", 1,
	1, wl_registry_requests,
	2, wl_registry_events
};
