package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.WLObject;

public class WLGlobal extends WLObject {
	
	public WLGlobal() {
	}
	
	public WLGlobal(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	@Override
	public String toString() {
		return "GLOBAL(0x" + Long.toHexString(native_ptr) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLGlobal) {
			if(((WLGlobal) obj).native_ptr == native_ptr) return true;
		}
		return false;
	}
	
	public static interface WLGlobalBindListener {
		
		public void bind(long client, int version, int id);
		
	}
}
