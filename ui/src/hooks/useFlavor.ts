import { useState, useEffect, useCallback, useRef } from 'react';

export interface FlavorMessage {
  type: string;
  payload?: any;
}

type MessageHandler = (message: FlavorMessage) => void;

class FlavorBridge {
  private handlers: Map<string, Set<MessageHandler>> = new Map();
  private isWebView2 = false;

  constructor() {
    this.isWebView2 = !!(window.chrome?.webview);
    
    if (this.isWebView2) {
      window.chrome!.webview!.addEventListener('message', (event: any) => {
        this.handleMessage(event.data);
      });
    }
  }

  private handleMessage(data: string | FlavorMessage) {
    try {
      const message: FlavorMessage = typeof data === 'string' ? JSON.parse(data) : data;
      const handlers = this.handlers.get(message.type);
      if (handlers) {
        handlers.forEach(handler => handler(message));
      }
      
      const allHandlers = this.handlers.get('*');
      if (allHandlers) {
        allHandlers.forEach(handler => handler(message));
      }
    } catch (e) {
      console.error('[Flavor] Failed to parse message:', e);
    }
  }

  subscribe(type: string, handler: MessageHandler): () => void {
    if (!this.handlers.has(type)) {
      this.handlers.set(type, new Set());
    }
    this.handlers.get(type)!.add(handler);
    
    return () => {
      this.handlers.get(type)?.delete(handler);
    };
  }

  send(type: string, payload?: any): void {
    const message: FlavorMessage = { type, payload };
    
    if (this.isWebView2) {
      window.chrome!.webview!.postMessage(JSON.stringify(message));
    } else {
      console.log('[Flavor] Send (dev mode):', message);
    }
  }

  get isConnected(): boolean {
    return this.isWebView2;
  }
}

const flavorBridge = new FlavorBridge();

export function useFlavor() {
  return {
    send: flavorBridge.send.bind(flavorBridge),
    isConnected: flavorBridge.isConnected,
  };
}

export function useFlavorMessage(type: string, handler: MessageHandler) {
  const handlerRef = useRef(handler);
  handlerRef.current = handler;

  useEffect(() => {
    const unsubscribe = flavorBridge.subscribe(type, (msg) => {
      handlerRef.current(msg);
    });
    return unsubscribe;
  }, [type]);
}

export function useFlavorState<T>(type: string, initialValue: T): [T, (value: T) => void] {
  const [state, setState] = useState<T>(initialValue);

  useFlavorMessage(type, (msg) => {
    if (msg.payload !== undefined) {
      setState(msg.payload as T);
    }
  });

  const updateState = useCallback((value: T) => {
    setState(value);
    flavorBridge.send(type, value);
  }, [type]);

  return [state, updateState];
}

export default flavorBridge;
