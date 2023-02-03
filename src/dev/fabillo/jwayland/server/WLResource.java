package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.JWayland;
import dev.fabillo.jwayland.WLObject;

public class WLResource extends WLObject {
	
	public WLResource() {
	}
	
	public WLResource(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	public native long get_client();
	
	@Override
	public String toString() {
		return "RESOURCE(0x" + Long.toHexString(native_ptr) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLResource) {
			if(((WLResource) obj).native_ptr == native_ptr) return true;
		}
		return false;
	}
	
	static {
		JWayland.loadLibrary();
	}

}
