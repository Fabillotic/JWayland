package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.JWayland;
import dev.fabillo.jwayland.WLObject;

public class WLClient extends WLObject {
	
	public WLClient() {
	}
	
	public WLClient(long native_ptr) {
		super(native_ptr);
	}
	
	public native void addDestroyListener(WLClientDestroyedListener listener);
	
	@Override
	public String toString() {
		return "CLIENT(0x" + Long.toHexString(getPointer()) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLClient) {
			if(((WLClient) obj).getPointer() == getPointer()) return true;
		}
		return false;
	}
	
	public static interface WLClientCreatedListener {
		
		public void client_created(WLClient client);
		
	}
	
	public static interface WLClientDestroyedListener {
		
		public void client_destroyed(WLClient client);
		
	}
	
	static {
		JWayland.loadLibrary();
	}

}
