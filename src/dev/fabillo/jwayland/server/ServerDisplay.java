package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.server.WLClient.WLClientCreatedListener;
import dev.fabillo.jwayland.server.WLGlobal.WLGlobalBindListener;

public class ServerDisplay {
	
	public long native_ptr = 0;
	
	private ServerDisplay() {
	}
	
	public static ServerDisplay create() {
		ServerDisplay display = new ServerDisplay();
		display.create_native();
		if(display.native_ptr == 0) {
			return null;
		}
		return display;
	}
	
	private static native void init_jni();
	private native void create_native();
	
	public native void run();
	public native void terminate();
	public native void flush_clients();
	public native String add_socket_auto();
	public native boolean add_socket_fd(int fd);
	public native boolean add_socket(String name);
	public native void destroy_clients();
	public native void destroy();
	
	public native void init_shm();
	
	public native WLGlobal create_global(String interface_name, int version, WLGlobalBindListener listener);
	public native WLResource create_resource(long client, String interface_name, int version, int id);
	public native WLEventLoop get_event_loop();
	
	public native void add_client_created_listener(WLClientCreatedListener listener);
	
	static {
		System.loadLibrary("jwayland");
		init_jni();
	}
	
}
