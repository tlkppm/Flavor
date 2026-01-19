/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        game: {
          bg: 'rgba(20, 20, 30, 0.95)',
          border: 'rgba(255, 255, 255, 0.1)',
          accent: '#FFD700', // 金色，非赛博朋克
          text: '#E0E0E0',
        }
      },
      boxShadow: {
        'glow': '0 0 15px rgba(255, 215, 0, 0.3)',
      }
    },
  },
  plugins: [],
}