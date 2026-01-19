import { useState, useEffect } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faBars, faTimes, faInfoCircle, faCog, faGamepad } from '@fortawesome/free-solid-svg-icons';

// 模拟 C++ 通信接口
declare global {
  interface Window {
    chrome?: {
      webview?: {
        postMessage: (message: any) => void;
        addEventListener: (type: string, listener: (event: any) => void) => void;
        removeEventListener: (type: string, listener: (event: any) => void) => void;
      }
    }
  }
}

function App() {
  const [isPanelOpen, setIsPanelOpen] = useState(true);
  const [position, setPosition] = useState({ x: 50, y: 50 });
  const [isDragging, setIsDragging] = useState(false);

  // 处理拖拽逻辑
  useEffect(() => {
    const handleMouseMove = (e: MouseEvent) => {
      if (isDragging) {
        setPosition(prev => ({
          x: prev.x + e.movementX,
          y: prev.y + e.movementY
        }));
      }
    };

    const handleMouseUp = () => {
      setIsDragging(false);
    };

    if (isDragging) {
      window.addEventListener('mousemove', handleMouseMove);
      window.addEventListener('mouseup', handleMouseUp);
    }

    return () => {
      window.removeEventListener('mousemove', handleMouseMove);
      window.removeEventListener('mouseup', handleMouseUp);
    };
  }, [isDragging]);

  return (
    <div className="w-screen h-screen relative overflow-hidden bg-[#0f0f14]">
      {/* 主悬浮窗口 */}
      <motion.div
        className="absolute pointer-events-auto bg-game-bg border border-game-border rounded-lg shadow-glow backdrop-blur-md overflow-hidden flex"
        style={{ 
          left: position.x, 
          top: position.y,
          width: isPanelOpen ? '600px' : '300px',
          height: '400px'
        }}
        animate={{ 
          width: isPanelOpen ? 600 : 300,
          boxShadow: isDragging ? '0 0 25px rgba(255, 215, 0, 0.5)' : '0 0 15px rgba(255, 215, 0, 0.2)'
        }}
        transition={{ type: "spring", stiffness: 300, damping: 30 }}
      >
        {/* 左侧主控制区 */}
        <div className="w-[300px] flex-shrink-0 flex flex-col h-full border-r border-game-border relative z-10 bg-game-bg">
          {/* 拖拽标题栏 */}
          <div 
            className="h-10 bg-white/5 flex items-center px-4 cursor-move select-none border-b border-game-border justify-between"
            onMouseDown={() => setIsDragging(true)}
          >
            <div className="flex items-center gap-2 text-game-accent font-bold">
              <FontAwesomeIcon icon={faGamepad} />
              <span>Flavor Menu</span>
            </div>
            <div className="flex gap-2">
               <button className="text-white/50 hover:text-white transition-colors">
                  <FontAwesomeIcon icon={faCog} />
               </button>
            </div>
          </div>

          {/* 内容区 */}
          <div className="flex-1 p-4 space-y-4 overflow-y-auto">
             <div className="space-y-2">
                <h3 className="text-xs uppercase tracking-wider text-white/40 font-bold">General</h3>
                <div className="flex items-center justify-between bg-white/5 p-3 rounded hover:bg-white/10 transition-colors cursor-pointer group">
                   <span className="text-sm">God Mode</span>
                   <div className="w-8 h-4 bg-game-accent/20 rounded-full relative">
                      <div className="absolute right-0 top-0 w-4 h-4 bg-game-accent rounded-full shadow-sm"></div>
                   </div>
                </div>
                <div className="flex items-center justify-between bg-white/5 p-3 rounded hover:bg-white/10 transition-colors cursor-pointer group">
                   <span className="text-sm">Infinite Ammo</span>
                   <div className="w-8 h-4 bg-white/10 rounded-full relative">
                      <div className="absolute left-0 top-0 w-4 h-4 bg-white/40 rounded-full shadow-sm"></div>
                   </div>
                </div>
             </div>

             <div className="space-y-2">
                <h3 className="text-xs uppercase tracking-wider text-white/40 font-bold">Visuals</h3>
                <div className="flex items-center justify-between bg-white/5 p-3 rounded hover:bg-white/10 transition-colors cursor-pointer">
                   <span className="text-sm">ESP</span>
                   <div className="text-xs text-game-accent">Enabled</div>
                </div>
             </div>
          </div>

          {/* 底部栏 */}
          <div className="h-12 border-t border-game-border flex items-center justify-between px-4 bg-white/5">
             <span className="text-xs text-white/30">v1.0.0</span>
             <button 
               onClick={() => setIsPanelOpen(!isPanelOpen)}
               className="text-game-accent hover:text-white transition-colors"
             >
               <FontAwesomeIcon icon={isPanelOpen ? faTimes : faBars} />
               <span className="ml-2 text-sm">{isPanelOpen ? 'Close Info' : 'More Info'}</span>
             </button>
          </div>
        </div>

        {/* 右侧可展开面板 */}
        <AnimatePresence>
          {isPanelOpen && (
            <motion.div
              initial={{ opacity: 0, x: -20 }}
              animate={{ opacity: 1, x: 0 }}
              exit={{ opacity: 0, x: -20 }}
              className="w-[300px] flex-shrink-0 bg-black/40 p-4 overflow-y-auto"
            >
               <div className="h-full flex flex-col">
                  <div className="flex items-center gap-2 text-white/80 mb-4 pb-2 border-b border-white/10">
                     <FontAwesomeIcon icon={faInfoCircle} />
                     <span className="font-bold">Status Log</span>
                  </div>
                  
                  <div className="space-y-3 text-xs font-mono">
                     <div className="flex gap-2">
                        <span className="text-green-400">[12:01:22]</span>
                        <span className="text-white/60">Module injected successfully</span>
                     </div>
                     <div className="flex gap-2">
                        <span className="text-blue-400">[12:01:23]</span>
                        <span className="text-white/60">Connected to game engine</span>
                     </div>
                     <div className="flex gap-2">
                        <span className="text-yellow-400">[12:01:25]</span>
                        <span className="text-white/60">Hook established at 0x7FF4D2</span>
                     </div>
                     <div className="flex gap-2">
                        <span className="text-white/30">...</span>
                     </div>
                  </div>

                  <div className="mt-auto pt-4 border-t border-white/10">
                     <h4 className="text-xs font-bold text-white/50 mb-2">Performance</h4>
                     <div className="flex justify-between text-xs mb-1">
                        <span className="text-white/40">Frame Time</span>
                        <span className="text-green-400">16.6ms</span>
                     </div>
                     <div className="flex justify-between text-xs">
                        <span className="text-white/40">Memory</span>
                        <span className="text-blue-400">42MB</span>
                     </div>
                  </div>
               </div>
            </motion.div>
          )}
        </AnimatePresence>
      </motion.div>
    </div>
  )
}

export default App
