package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.JWayland;
import dev.fabillo.jwayland.WLObject;

public class WLEventLoop extends WLObject {
	
	public WLEventLoop() {
	}
	
	public WLEventLoop(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	public native void dispatch(int timeout);
	
	@Override
	public String toString() {
		return "EVENT_LOOP(0x" + Long.toHexString(native_ptr) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLEventLoop) {
			if(((WLEventLoop) obj).native_ptr == native_ptr) return true;
		}
		return false;
	}
	
	static {
		JWayland.loadLibrary();
	}

}
