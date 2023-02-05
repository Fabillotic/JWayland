package dev.fabillo.jwayland;

public class WLFixed extends Number {
	
	private int data;
	
	public WLFixed() {
		this.data = 0;
	}
	
	public WLFixed(int data) {
		this.data = data;
	}
	
	public WLFixed(int integer, byte decimal) {
		if(integer > 8388607 || integer < -8388608) {
			throw new NumberFormatException("Integer component out of 24-bit range!");
		}
		this.data = (integer << 8) + (decimal & 255);
	}
	
	public WLFixed(int integer, int decimal) {
		if(integer > 8388607 || integer < -8388608) {
			throw new NumberFormatException("Integer component out of 24-bit range!");
		}
		if(decimal > 255 || decimal < 0) {
			throw new NumberFormatException("Decimal component out of 8-bit range!");
		}
		this.data = (integer << 8) + (decimal & 255);
	}
	
	public WLFixed(float f) {
		this((int) f, (byte) ((int) (Math.abs(f - (int) f) * 255.0f)));
	}
	
	/**
	 * @return the double conversion of the fixed value
	 */
	@Override
	public double doubleValue() {
		return (Math.abs(data >> 8) + ((data & 0xFF) / 255.0)) * ((data >> 8) >= 0 ? 1.0 : -1.0);
	}
	
	/**
	 * @return the float conversion of the fixed value
	 */
	@Override
	public float floatValue() {
		return (Math.abs(data >> 8) + ((data & 0xFF) / 255.0f)) * ((data >> 8) >= 0 ? 1.0f : -1.0f);
	}
	
	/**
	 * @return the raw internal signed 32-bit value
	 */
	public int rawValue() {
		return data;
	}
	
	/**
	 * @return the whole integer component (upper 24-bits) of the value
	 */
	@Override
	public int intValue() {
		return data >> 8;
	}
	
	@Override
	public long longValue() {
		return (long) intValue();
	}

}
