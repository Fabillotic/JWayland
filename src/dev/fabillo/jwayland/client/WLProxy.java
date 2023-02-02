package dev.fabillo.jwayland.client;

import dev.fabillo.jwayland.WLObject;

public class WLProxy extends WLObject {
	
	public WLProxy() {
	}
	
	public WLProxy(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	@Override
	public String toString() {
		return "PROXY(0x" + Long.toHexString(native_ptr) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLProxy) {
			if(((WLProxy) obj).native_ptr == native_ptr) return true;
		}
		return false;
	}
	
}
