package dev.fabillo.jwayland;

public abstract class WLObject {
	
	private long native_ptr = 0;
	
	public WLObject() {
	}
	
	public WLObject(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	public long getPointer() {
		return native_ptr;
	}
	
	@Override
	public int hashCode() {
		return (int) (getPointer()^(getPointer()>>>32));
	}

}
