// Cinder Skeleton for OpenGL

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class CinderSkeletonApp : public AppNative 
{
  public:
	void prepareSettings( Settings* settings );
	void setup();
	void mouseDown( MouseEvent event );
	void mouseMove( MouseEvent event );
	void keyDown( KeyEvent event );
	void resize( void );
	void update();
	void draw();
};

#include "GlutAppSkeleton.h"

TriAppSkeleton g_app;

void CinderSkeletonApp::prepareSettings( Settings *settings )
{
	settings->setFrameRate( 60.0f );
	settings->setWindowSize( g_app.w(), g_app.h() );
}

void CinderSkeletonApp::setup()
{
	g_app.initGL( 0, NULL );
	gl::enableVerticalSync();
}

void CinderSkeletonApp::mouseDown( MouseEvent event )
{
	g_app.mouseDown( 0, 0, event.getX(), event.getY() ); //Dummy
}

void CinderSkeletonApp::mouseMove( MouseEvent event )
{
	g_app.mouseMove( event.getX(), event.getY() );
}

void CinderSkeletonApp::keyDown( KeyEvent event )
{
	g_app.keyboard( event.getNativeKeyCode(), 0, 0 ); //Dummy
}

void CinderSkeletonApp::update()
{
}

void CinderSkeletonApp::draw()
{
	g_app.display();
}

void CinderSkeletonApp::resize( void )
{
	g_app.resize( this->getWindowWidth(), this->getWindowHeight() );
}

CINDER_APP_NATIVE( CinderSkeletonApp, RendererGl )