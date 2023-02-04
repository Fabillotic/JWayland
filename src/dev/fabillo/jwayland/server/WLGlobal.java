package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.WLObject;

public class WLGlobal extends WLObject {
	
	public WLGlobal() {
	}
	
	public WLGlobal(long native_ptr) {
		super(native_ptr);
	}
	
	@Override
	public String toString() {
		return "GLOBAL(0x" + Long.toHexString(getPointer()) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLGlobal) {
			if(((WLGlobal) obj).getPointer() == getPointer()) return true;
		}
		return false;
	}
	
	public static interface WLGlobalBindListener {
		
		public void bind(long client, int version, int id);
		
	}
}
