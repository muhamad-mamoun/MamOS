# MamOS - Real-Time Operating System Kernel
> Just a hobby, won't be big and professional like FreeRTOS ;)

MamOS is a priority-based real-time operating system (RTOS) designed for efficient task management in embedded systems. Built for the **STM32F401x** (ARM Cortex-M4) and architected for portability, MamOS offers key scheduling and synchronization features, making it a powerful foundation for real-time applications.

## 🚀 Key Features  
- **Priority-Based Scheduling:** Ensures high-priority tasks are executed promptly.  
- **Preemptive and Cooperative Scheduling:** Configurable to meet different application needs.  
- **Idle Task Power Optimization:** Switches to low-power mode during system idle time.  
- **Mutex Support:** Facilitates task synchronization and prevents race conditions.  
- **Portable Design:** Easy to port to other microcontrollers.

## 🔧 Future Work  
- **Memory Protection:** Prevent tasks from accessing or corrupting each other’s memory.  
- **Enhanced Error Handling:** Improve fault detection and recovery mechanisms.  
- **More APIs:** Provide APIs for easier management of tasks and resources.  

## 💻 Getting Started  
1. **Clone the repository**:  
   ```bash
   git clone https://github.com/muhamad-mamoun/MamOS.git
   ```
2. **Integrate the Kernel**:
   - Copy the `MamOS` folder into your project's `SERVICES` directory or any suitable location within your project structure.

3. **Configure the Kernel**:
   - Open `MamOSConfig.h` and modify the configuration settings to suit your application's requirements. This may include setting task priorities, stack sizes, and enabling or disabling specific features.

4. **Utilize the APIs**:
   - Incorporate the kernel by including the `MamOS.h` header in your source files. Leverage the available APIs to manage tasks, synchronize resources, and configure the kernel behavior as needed.

5. **Build and Test**:
   - Compile your project and upload it to your target hardware. Thoroughly test the functionality of your application to ensure proper task management and performance.

## 🤝 Contribute  
Feel free to fork the project, submit pull requests, or suggest improvements!

## 📄 License  
This project is licensed under the **GNU General Public License v3.0**. See the [LICENSE](LICENSE) file for details.
