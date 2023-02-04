package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.JWayland;
import dev.fabillo.jwayland.WLObject;

public class WLResource extends WLObject {
	
	public WLResource() {
	}
	
	public WLResource(long native_ptr) {
		super(native_ptr);
	}
	
	public native long get_client();
	
	@Override
	public String toString() {
		return "RESOURCE(0x" + Long.toHexString(getPointer()) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLResource) {
			if(((WLResource) obj).getPointer() == getPointer()) return true;
		}
		return false;
	}
	
	static {
		JWayland.loadLibrary();
	}

}
