package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.JWayland;
import dev.fabillo.jwayland.WLObject;

public class WLEventLoop extends WLObject {
	
	public WLEventLoop() {
	}
	
	public WLEventLoop(long native_ptr) {
		super(native_ptr);
	}
	
	public native void dispatch(int timeout);
	
	@Override
	public String toString() {
		return "EVENT_LOOP(0x" + Long.toHexString(getPointer()) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLEventLoop) {
			if(((WLEventLoop) obj).getPointer() == getPointer()) return true;
		}
		return false;
	}
	
	static {
		JWayland.loadLibrary();
	}

}
