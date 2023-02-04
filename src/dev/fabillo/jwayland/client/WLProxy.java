package dev.fabillo.jwayland.client;

import dev.fabillo.jwayland.WLObject;

public class WLProxy extends WLObject {
	
	public WLProxy() {
	}
	
	public WLProxy(long native_ptr) {
		super(native_ptr);
	}
	
	@Override
	public String toString() {
		return "PROXY(0x" + Long.toHexString(getPointer()) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLProxy) {
			if(((WLProxy) obj).getPointer() == getPointer()) return true;
		}
		return false;
	}
	
}
