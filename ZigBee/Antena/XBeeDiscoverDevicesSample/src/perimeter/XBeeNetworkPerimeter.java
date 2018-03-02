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


import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import com.digi.xbee.api.*;
import com.digi.xbee.api.exceptions.*;
import com.digi.xbee.api.listeners.*;
import com.digi.xbee.api.models.*;


/**
 * This class represents an XBee Network.
 *  
 * <p>The network allows the discovery of remote devices in the same network 
 * as the local one and stores them.</p>
 */
public class XBeeNetworkPerimeter {
	
	// Variables.

	private XBeeNetwork myXBeeNetwork;
	private NodeDiscoveryPersonal nodeDiscovery;
	private List<IDiscoveryListener> discoveryListeners = new ArrayList <IDiscoveryListener>();
	
	/**
	 * Instantiates a new {@code XBeeNetwork} object.
	 * 
	 * @param device Local XBee device to get the network from.
	 * 
	 * @throws NullPointerException if {@code device == null}.
	 * 
	 * @see XBeeDevice
	 */
	XBeeNetworkPerimeter(XBeeNetwork myXBeeNetwork, XBeeDevice device) {
		if (device == null)
			throw new NullPointerException("Local XBee device cannot be null.");
		
		this.myXBeeNetwork = myXBeeNetwork;
		this.nodeDiscovery = new NodeDiscoveryPersonal(device);
	}
	
	/**
	 * Discovers and reports the first remote XBee device that matches the 
	 * supplied identifier.
	 * 
	 * <p>This method blocks until the device is discovered or the configured 
	 * timeout expires. To configure the discovery timeout, use the method
	 * {@link #setDiscoveryTimeout(long)}.</p>
	 * 
	 * <p>To configure the discovery options, use the 
	 * {@link #setDiscoveryOptions(Set)} method.</p> 
	 * 
	 * @param id The identifier of the device to be discovered.
	 * 
	 * @return The discovered remote XBee device with the given identifier, 
	 *         {@code null} if the timeout expires and the device was not found.
	 * 
	 * @throws IllegalArgumentException if {@code id.length() == 0}.
	 * @throws InterfaceNotOpenException if the device is not open.
	 * @throws NullPointerException if {@code id == null}.
	 * @throws XBeeException if there is an error discovering the device.
	 * 
	 * @see #discoverDevices(List)
	 * @see #getDevice(String)
	 * @see RemoteXBeeDevice
	 */
	public RemoteXBeeDevice discoverDevice(String id) throws XBeeException {
		return myXBeeNetwork.discoverDevice(id);
	}
	
	/**
	 * Discovers and reports all remote XBee devices that match the supplied 
	 * identifiers.
	 * 
	 * <p>This method blocks until the configured timeout expires. To configure 
	 * the discovery timeout, use the method {@link #setDiscoveryTimeout(long)}.
	 * </p>
	 * 
	 * <p>To configure the discovery options, use the 
	 * {@link #setDiscoveryOptions(Set)} method.</p> 
	 * 
	 * @param ids List which contains the identifiers of the devices to be 
	 *            discovered.
	 * 
	 * @return A list of the discovered remote XBee devices with the given 
	 *         identifiers.
	 * 
	 * @throws IllegalArgumentException if {@code ids.size() == 0}.
	 * @throws InterfaceNotOpenException if the device is not open.
	 * @throws NullPointerException if {@code ids == null}.
	 * @throws XBeeException if there is an error discovering the devices.
	 * 
	 * @see #discoverDevice(String)
	 * @see RemoteXBeeDevice
	 */
	public List<RemoteXBeeDevice> discoverDevices(List<String> ids) throws XBeeException {
		return myXBeeNetwork.discoverDevices(ids);
	}
	
	/**
	 * Adds the given discovery listener to the list of listeners to be notified 
	 * when the discovery process is running.
	 * 
	 * <p>If the listener has already been included, this method does nothing.
	 * </p>
	 * 
	 * @param listener Listener to be notified when the discovery process is
	 *                 running.
	 * 
	 * @throws NullPointerException if {@code listener == null}.
	 * 
	 * @see com.digi.xbee.api.listeners.IDiscoveryListener
	 * @see #removeDiscoveryListener(IDiscoveryListener)
	 */
	public void addDiscoveryListener(IDiscoveryListener listener) {
		myXBeeNetwork.addDiscoveryListener(listener);
		
		if (listener == null)
			throw new NullPointerException("Listener cannot be null.");
		
		synchronized (discoveryListeners) {
			if (!discoveryListeners.contains(listener))
				discoveryListeners.add(listener);
		}
	}
	
	/**
	 * Removes the given discovery listener from the list of discovery 
	 * listeners.
	 * 
	 * <p>If the listener is not included in the list, this method does nothing.
	 * </p>
	 * 
	 * @param listener Discovery listener to remove.
	 * 
	 * @throws NullPointerException if {@code listener == null}.
	 * 
	 * @see com.digi.xbee.api.listeners.IDiscoveryListener
	 * @see #addDiscoveryListener(IDiscoveryListener)
	 */
	public void removeDiscoveryListener(IDiscoveryListener listener) {
		myXBeeNetwork.removeDiscoveryListener(listener);
		
		if (listener == null)
			throw new NullPointerException("Listener cannot be null.");
		
		synchronized (discoveryListeners) {
			if (discoveryListeners.contains(listener))
				discoveryListeners.remove(listener);
		}
	}
	
	/**
	 * Starts the discovery process with the configured timeout and options.
	 * 
	 * <p>To be notified every time an XBee device is discovered, add a
	 * {@code IDiscoveryListener} using the 
	 * {@link #addDiscoveryListener(IDiscoveryListener)} method before starting
	 * the discovery process.</p>
	 * 
	 * <p>To configure the discovery timeout, use the 
	 * {@link #setDiscoveryTimeout(long)} method.</p>
	 * 
	 * <p>To configure the discovery options, use the 
	 * {@link #setDiscoveryOptions(Set)} method.</p> 
	 * 
	 * @throws IllegalStateException if the discovery process is already running.
	 * @throws InterfaceNotOpenException if the device is not open.
	 * 
	 * @see #addDiscoveryListener(IDiscoveryListener)
	 * @see #stopDiscoveryProcess()
	 */
	public void startPersonalDiscoveryProcess() {
		if (isDiscoveryRunning())
			throw new IllegalStateException("The discovery process is already running.");
		
		synchronized (discoveryListeners) {
			nodeDiscovery.startDiscoveryProcess(discoveryListeners);
		}		
	}
	
	/**
	 * Stops the discovery process if it is running.
	 * 
	 * <p>Note that DigiMesh/DigiPoint devices are blocked until the discovery
	 * time configured (NT parameter) has elapsed, so if you try to get/set
	 * any parameter during the discovery process you will receive a timeout 
	 * exception.</p>
	 * 
	 * @see #isDiscoveryRunning()
	 * @see #removeDiscoveryListener(IDiscoveryListener)
	 * @see #startDiscoveryProcess()
	 */
	public void stopDiscoveryProcess() {
		myXBeeNetwork.stopDiscoveryProcess();
	}
	
	/**
	 * Retrieves whether the discovery process is running or not.
	 * 
	 * @return {@code true} if the discovery process is running, {@code false} 
	 *         otherwise.
	 * 
	 * @see #startDiscoveryProcess()
	 * @see #stopDiscoveryProcess()
	 */
	public boolean isDiscoveryRunning() {
		return myXBeeNetwork.isDiscoveryRunning();
	}
	
	/**
	 * Configures the discovery timeout ({@code NT} parameter) with the given 
	 * value.
	 * 
	 * <p>Note that in some protocols, the discovery process may take longer
	 * than the value set in this method due to the network propagation time.
	 * </p>
	 * 
	 * @param timeout New discovery timeout in milliseconds.
	 * 
	 * @throws TimeoutException if there is a timeout setting the discovery
	 *                          timeout.
	 * @throws XBeeException if there is any other XBee related exception.
	 * 
	 * @see #setDiscoveryOptions(Set)
	 */
	public void setDiscoveryTimeout(long timeout) throws TimeoutException, XBeeException {
		myXBeeNetwork.setDiscoveryTimeout(timeout);
	}
	
	/**
	 * Configures the discovery options ({@code NO} parameter) with the given 
	 * value.
	 * 
	 * @param options New discovery options.
	 * 
	 * @throws TimeoutException if there is a timeout setting the discovery
	 *                          options.
	 * @throws XBeeException if there is any other XBee related exception.
	 * 
	 * @see #setDiscoveryTimeout(long)
	 * @see DiscoveryOptions
	 */
	public void setDiscoveryOptions(Set<DiscoveryOptions> options) throws TimeoutException, XBeeException {
		myXBeeNetwork.setDiscoveryOptions(options);
	}
	
	/**
	 * Returns all remote devices already contained in the network.
	 * 
	 * <p>Note that this method <b>does not perform a discovery</b>, only 
	 * returns the devices that have been previously discovered.</p>
	 * 
	 * @return A list with all XBee devices in the network.
	 * 
	 * @see #getDevices(String)
	 * @see RemoteXBeeDevice
	 */
	public List<RemoteXBeeDevice> getDevices() {
		return myXBeeNetwork.getDevices();
	}
	
	/**
	 * Returns all remote devices that match the supplied identifier.
	 * 
	 * <p>Note that this method <b>does not perform a discovery</b>, only 
	 * returns the devices that have been previously discovered.</p>
	 * 
	 * @param id The identifier of the devices to be retrieved.
	 * 
	 * @return A list of the remote XBee devices contained in the network with 
	 *         the given identifier.
	 * 
	 * @throws IllegalArgumentException if {@code id.length() == 0}.
	 * @throws NullPointerException if {@code id == null}.
	 * 
	 * @see #getDevice(String)
	 * @see RemoteXBeeDevice
	 */
	public List<RemoteXBeeDevice> getDevices(String id) {
		return myXBeeNetwork.getDevices(id);
	}
	
	/**
	 * Returns the first remote device that matches the supplied identifier.
	 * 
	 * <p>Note that this method <b>does not perform a discovery</b>, only 
	 * returns the device that has been previously discovered.</p>
	 * 
	 * @param id The identifier of the device to be retrieved.
	 * 
	 * @return The remote XBee device contained in the network with the given 
	 *         identifier, {@code null} if the network does not contain any 
	 *         device with that Node ID.
	 * 
	 * @throws IllegalArgumentException if {@code id.length() == 0}.
	 * @throws NullPointerException if {@code id == null}.
	 * 
	 * @see #discoverDevice(String)
	 * @see #getDevices(String)
	 * @see RemoteXBeeDevice
	 */
	public RemoteXBeeDevice getDevice(String id) {
		return myXBeeNetwork.getDevice(id);
	}
	
	/**
	 * Returns the remote device already contained in the network whose 64-bit 
	 * address matches the given one.
	 * 
	 * <p>Note that this method <b>does not perform a discovery</b>, only 
	 * returns the device that has been previously discovered.</p>
	 * 
	 * @param address The 64-bit address of the device to be retrieved.
	 * 
	 * @return The remote device in the network or {@code null} if it is not 
	 *         found.
	 * 
	 * @throws IllegalArgumentException if {@code address.equals(XBee64BitAddress.UNKNOWN_ADDRESS)}.
	 * @throws NullPointerException if {@code address == null}.
	 */
	public RemoteXBeeDevice getDevice(XBee64BitAddress address) {
		return myXBeeNetwork.getDevice(address);
	}
	
	/**
	 * Returns the remote device already contained in the network whose 16-bit 
	 * address matches the given one.
	 * 
	 * <p>Note that this method <b>does not perform a discovery</b>, only 
	 * returns the device that has been previously discovered.</p>
	 * 
	 * @param address The 16-bit address of the device to be retrieved.
	 * 
	 * @return The remote device in the network or {@code null} if it is not 
	 *         found.
	 * 
	 * @throws IllegalArgumentException if {@code address.equals(XBee16BitAddress.UNKNOWN_ADDRESS)}.
	 * @throws NullPointerException if {@code address == null}.
	 * @throws OperationNotSupportedException if the protocol of the local XBee device is DigiMesh or Point-to-Multipoint.
	 */
	public RemoteXBeeDevice getDevice(XBee16BitAddress address) throws OperationNotSupportedException {
		return myXBeeNetwork.getDevice(address);
	}
	
	/**
	 * Adds the given remote device to the network. 
	 * 
	 * <p>Notice that this operation does not join the remote XBee device to the
	 * network; it just tells the network that it contains that device. However, 
	 * the device has only been added to the device list, and may not be 
	 * physically in the same network.</p>
	 * 
	 * <p>The way of adding a device to the network is based on the 64-bit 
	 * address. If it is not configured:</p>
	 * 
	 * <ul>
	 * <li>For 802.15.4 and ZigBee devices, it will use the 16-bit address.</li>
	 * <li>For the rest will return {@code false} as the result of the addition.</li>
	 * </ul>
	 * 
	 * @param remoteDevice The remote device to be added to the network.
	 * 
	 * @return The remote XBee Device instance in the network, {@code null} if
	 *         the device could not be successfully added.
	 * 
	 * @throws NullPointerException if {@code remoteDevice == null}.
	 * 
	 * @see #addRemoteDevices(List)
	 * @see #removeRemoteDevice(RemoteXBeeDevice)
	 * @see RemoteXBeeDevice
	 */
	public RemoteXBeeDevice addRemoteDevice(RemoteXBeeDevice remoteDevice) {
		return myXBeeNetwork.addRemoteDevice(remoteDevice);
	}
	
	/**
	 * Adds the given list of remote devices to the network.
	 * 
	 * <p>Notice that this operation does not join the remote XBee devices to 
	 * the network; it just tells the network that it contains those devices. 
	 * However, the devices have only been added to the device list, and may 
	 * not be physically in the same network.</p>
	 * 
	 * <p>The way of adding a device to the network is based on the 64-bit 
	 * address. If it is not configured:</p>
	 * 
	 * <ul>
	 * <li>For 802.15.4 and ZigBee devices, the 16-bit address will be used instead.</li>
	 * <li>For the rest will return {@code false} as the result of the addition.</li>
	 * </ul>
	 * 
	 * @param list The list of remote devices to be added to the network.
	 * 
	 * @return A list with the successfully added devices to the network.
	 * 
	 * @throws NullPointerException if {@code list == null}.
	 * 
	 * @see #addRemoteDevice(RemoteXBeeDevice)
	 * @see RemoteXBeeDevice
	 */
	public List<RemoteXBeeDevice> addRemoteDevices(List<RemoteXBeeDevice> list) {
		return myXBeeNetwork.addRemoteDevices(list);
	}
	
	/**
	 * Removes the given remote XBee device from the network.
	 * 
	 * <p>Notice that this operation does not remove the remote XBee device 
	 * from the actual XBee network; it just tells the network object that it 
	 * will no longer contain that device. However, next time a discovery is 
	 * performed, it could be added again automatically.</p>
	 * 
	 * <p>This method will check for a device that matches the 64-bit address 
	 * of the provided one, if found, that device will be removed from the 
	 * corresponding list. In case the 64-bit address is not defined, it will 
	 * use the 16-bit address for DigiMesh and ZigBee devices.</p>
	 * 
	 * @param remoteDevice The remote device to be removed from the network.
	 * 
	 * @throws NullPointerException if {@code RemoteDevice == null}.
	 * 
	 * @see #addRemoteDevice(RemoteXBeeDevice)
	 * @see #clearDeviceList()
	 * @see RemoteXBeeDevice
	 */
	public void removeRemoteDevice(RemoteXBeeDevice remoteDevice) {
		myXBeeNetwork.removeRemoteDevice(remoteDevice);
	}
	
	/**
	 * Removes all the devices from this network. 
	 * 
	 * <p>The network will be empty after this call returns.</p>
	 * 
	 * <p>Notice that this does not imply removing the XBee devices from the 
	 * actual XBee network; it just tells the object that the list should be 
	 * empty now. Next time a discovery is performed, the list could be filled 
	 * with the remote XBee devices found.</p>
	 * 
	 * @see #removeRemoteDevice(RemoteXBeeDevice)
	 */
	public void clearDeviceList() {
		myXBeeNetwork.clearDeviceList();
	}
	
	/**
	 * Returns the number of devices already discovered in this network.
	 * 
	 * @return The number of devices already discovered in this network.
	 */
	public int getNumberOfDevices() {
		return myXBeeNetwork.getNumberOfDevices();
	}
	
	/*
	 * (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString(){
		return myXBeeNetwork.toString();
	}
}
