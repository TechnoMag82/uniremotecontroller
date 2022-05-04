package com.technomag.wirelesscontroller

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.GlobalScope
import kotlinx.coroutines.launch
import java.net.DatagramPacket
import java.net.DatagramSocket
import java.net.InetAddress

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        findViewById<Button>(R.id.button_power_off)?.setOnClickListener {
            sendMessage("1000")
        }
        findViewById<Button>(R.id.button_volume_up)?.setOnClickListener {
            sendMessage("4001")
        }
        findViewById<Button>(R.id.button_volume_down)?.setOnClickListener {
            sendMessage("4002")
        }
        findViewById<Button>(R.id.button_play_next)?.setOnClickListener {
            sendMessage("2000")
        }
        findViewById<Button>(R.id.button_play_prev)?.setOnClickListener {
            sendMessage("2001")
        }
        findViewById<Button>(R.id.button_play)?.setOnClickListener {
            sendMessage("2002")
        }
        findViewById<Button>(R.id.button_pause)?.setOnClickListener {
            sendMessage("2003")
        }
    }

    private fun sendMessage(message: String) {
        GlobalScope.launch(Dispatchers.IO) {
            val serverAddr = InetAddress.getByName("192.168.0.242")
            val bytes = message.toByteArray()
            val packet = DatagramPacket(bytes, bytes.size, serverAddr, 8389)
            try {
                DatagramSocket().use {
                    it.send(packet)
                }
            } catch (e: Exception) {
                Log.d("Datagram", "${e.message}")
            }
        }
    }
}