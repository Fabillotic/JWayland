package dev.fabillo.jwayland;

public class InterfaceNotFoundException extends Exception {
	
	public InterfaceNotFoundException(String iface) {
		super("Failed to locate '" + iface + "'!");
	}
	
}
