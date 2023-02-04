package dev.fabillo.jwayland.client;

import dev.fabillo.jwayland.JWayland;
import dev.fabillo.jwayland.WLObject;
import dev.fabillo.jwayland.protocol.client.WLDisplayProxy;

public class ClientDisplay extends WLObject {
	
	private ClientDisplay() {
	}
	
	public static ClientDisplay connect(String name) {
		ClientDisplay display = new ClientDisplay();
		display.connect_name(name);
		if(display.getPointer() == 0) {
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
		WLDisplayProxy display = new WLDisplayProxy(getPointer());
		return display;
	}
	
	public native void disconnect();
	public native void dispatch();
	public native void flush();
	public native void roundtrip();
	
	static {
		JWayland.loadLibrary();
		init_jni();
	}
	
}
