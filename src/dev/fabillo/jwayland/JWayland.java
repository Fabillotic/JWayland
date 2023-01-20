package dev.fabillo.jwayland;

public class JWayland {

	public static void main(String[] args) {
		ClientDisplay display = ClientDisplay.connect("wayland-0");
		
		display.roundtrip();
		
		display.disconnect();
	}

}
