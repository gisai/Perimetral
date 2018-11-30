/**
 * Copyright 2017, Digi International Inc.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, you can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES 
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES 
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF 
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
package perimeter;

import java.util.HashSet;
import java.util.Set;

import com.digi.xbee.api.*;
import com.digi.xbee.api.exceptions.*;
import com.digi.xbee.api.models.DiscoveryOptions;
import com.digi.xbee.api.utils.ByteUtils;

/**
 * XBee Java Library Discover Devices sample application.
 * 
 * <p>This example retrieves the XBee network from the local XBee device and 
 * performs a remote device discovery.</p>
 * 
 * <p>For a complete description on the example, refer to the 'ReadMe.txt' file
 * included in the root directory.</p>
 */
public class MainApp {

	/* Constants */
	
	// TODO Replace with the serial port where your module is connected to.
	private static final String PORT = "/dev/ttyUSB0";
	// TODO Replace with the baud rate of your module.
	private static final int BAUD_RATE = 9600;
	
	/**
	 * Application main method.
	 * 
	 * @param args Command line arguments.
	 */
	public static void main(String[] args) {
		System.out.println(" +-------------------------------------------+");
		System.out.println(" | Inicialización de la antena ZigBee        |");
		System.out.println(" +-------------------------------------------+\n");
		
		XBeeDevice myDevice = new XBeeDevice(PORT, BAUD_RATE);
		
		try {			
			myDevice.open();
			
			XBeeNetwork myXBeeNetwork = myDevice.getNetwork();
			XBeeNetworkPerimeter myXBeeNetworkPerimeter = new XBeeNetworkPerimeter (myXBeeNetwork,myDevice);
					
			Set<DiscoveryOptions> options = new HashSet <DiscoveryOptions> ();
			options.add(DiscoveryOptions.APPEND_DD);
			options.add(DiscoveryOptions.APPEND_RSSI);
			myXBeeNetworkPerimeter.setDiscoveryOptions(options);
			
			MyDiscoveryListener listener = new MyDiscoveryListener();
			
			myXBeeNetworkPerimeter.addDiscoveryListener(listener);
			System.out.println("\n>> Discovering remote XBee devices...");
			
			myXBeeNetworkPerimeter.startPersonalDiscoveryProcess();		
			
			while (true) {
				int RSSI = 0;
				try {
					RSSI = -ByteUtils.byteArrayToInt(myDevice.getParameter("DB"));
				} catch (TimeoutException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (XBeeException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				listener.setRSSI(RSSI);
		  }
			
		} catch (XBeeException e) {
			e.printStackTrace();
			myDevice.close();
			System.exit(1);
		}
	}
}
