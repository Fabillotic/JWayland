package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.JWayland;
import dev.fabillo.jwayland.WLObject;

public class WLResource extends WLObject {
	
	public WLResource() {
	}
	
	public WLResource(long native_ptr) {
		super(native_ptr);
	}
	
	public native WLClient get_client();
	public native void addDestroyListener(WLResourceDestroyedListener listener);
	
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
	
	public static interface WLResourceDestroyedListener {
		
		public void resource_destroyed(WLResource resource);
		
	}
	
	static {
		JWayland.loadLibrary();
	}

}
