/*
 * Copyright 2011-2022 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#ifndef BGFX_GLCONTEXT_EGL_H_HEADER_GUARD
#define BGFX_GLCONTEXT_EGL_H_HEADER_GUARD

#if BGFX_USE_EGL

#include <EGL/egl.h>
#include <EGL/eglext.h>
#if defined(Success)
// X11 defines Success
#	undef Success
#endif // defined(Success)

namespace bgfx { namespace gl
{
    struct SwapChainGL;
    struct SwapChainEGL;
    struct EglContext
	{
        EglContext()
			: m_current(NULL)
			, m_context(NULL)
			, m_display(NULL)
			, m_surface(NULL)
			, m_msaaContext(false)
		{
		}

		void create(uint32_t _width, uint32_t _height, uint32_t _flags);
		void destroy();
		void resize(uint32_t _width, uint32_t _height, uint32_t _flags);

		uint64_t getCaps() const;
        //SwapChainGL just use as a pointer handle outside
        SwapChainGL* createSwapChain(void* _nwh);
        void destroySwapChain(SwapChainGL*  _swapChain);
        void swap(SwapChainGL* _swapChain = NULL);
        void makeCurrent(SwapChainGL* _swapChain = NULL);

		void import();

		bool isValid() const
		{
			return NULL != m_context;
		}
        EGLContext currentContext();
		void* m_eglLibrary;
        SwapChainEGL* m_current;
		EGLConfig  m_config;
		EGLContext m_context;
		EGLDisplay m_display;
		EGLSurface m_surface;
		// true when MSAA is handled by the context instead of using MSAA FBO
		bool m_msaaContext;
	};
} /* namespace gl */ } // namespace bgfx
#else
#include <inttypes.h>
namespace bgfx { namespace gl
{
    struct SwapChainGL;
    struct EglContext{
        void create(uint32_t _width, uint32_t _height, uint32_t _flags){}
        void destroy(){}
        void resize(uint32_t _width, uint32_t _height, uint32_t _flags){}
        uint64_t getCaps() const {return 0;}
        SwapChainGL* createSwapChain(void* _nwh){return 0;}
        void destroySwapChain(SwapChainGL*  _swapChain){}
        void swap(SwapChainGL* _swapChain = nullptr){}
        void makeCurrent(SwapChainGL* _swapChain = nullptr){}
        void import(){}
        bool isValid() const{return false;}
        EGLContext currentContext()(return NULL;)
    };
}
}

#endif // BGFX_USE_EGL

#endif // BGFX_GLCONTEXT_EGL_H_HEADER_GUARD
