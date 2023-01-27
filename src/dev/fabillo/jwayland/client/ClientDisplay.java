package dev.fabillo.jwayland.client;

import dev.fabillo.jwayland.protocol.client.WLDisplayProxy;

public class ClientDisplay {
	
	public long native_ptr = 0;
	
	private ClientDisplay() {
	}
	
	public static ClientDisplay connect(String name) {
		ClientDisplay display = new ClientDisplay();
		display.connect_name(name);
		if(display.native_ptr == 0) {
			return null;
		}
		return display;
	}
	
	public static ClientDisplay connect(int fd) {
		ClientDisplay display = new ClientDisplay();
		display.connect_fd(fd);
		return display;
	}
	
	private static native void init_jni();
	private native void connect_name(String name);
	private native void connect_fd(int fd);
	
	public WLDisplayProxy getProxy() {
		WLDisplayProxy display = new WLDisplayProxy();
		display.native_ptr = native_ptr;
		return display;
	}
	
	public native void disconnect();
	public native void dispatch();
	public native void flush();
	public native void roundtrip();
	
	static {
		System.loadLibrary("jwayland");
		init_jni();
	}
	
}
