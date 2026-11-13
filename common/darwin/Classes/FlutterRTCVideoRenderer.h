#import "FlutterWebRTCPlugin.h"

#import <WebRTC/RTCMediaStream.h>
#import <WebRTC/RTCVideoFrame.h>
#import <WebRTC/RTCVideoRenderer.h>
#import <WebRTC/RTCVideoTrack.h>

@interface FlutterRTCVideoRenderer
    : NSObject <FlutterTexture, RTCVideoRenderer, FlutterStreamHandler>

/**
 * The {@link RTCVideoTrack}, if any, which this instance renders.
 */
@property(nonatomic, strong) RTCVideoTrack* videoTrack;
@property(nonatomic) int64_t textureId;
@property(nonatomic, weak) id<FlutterTextureRegistry> registry;
@property(nonatomic, strong) FlutterEventSink eventSink;

- (instancetype)initWithTextureRegistry:(id<FlutterTextureRegistry>)registry
                              messenger:(NSObject<FlutterBinaryMessenger>*)messenger;

- (void)dispose;

/**
 * Stops this renderer from calling the texture registry, without calling into
 * the engine. For when the engine is about to be destroyed (see
 * -[FlutterWebRTCPlugin detachRenderersFromEngine]).
 *
 * Main thread only, and irreversible: the renderer never renders again. Use
 * it only when the engine is being destroyed (app termination or scene
 * disconnect).
 */
- (void)detachFromEngine;

@end

@interface FlutterWebRTCPlugin (FlutterVideoRendererManager)

- (FlutterRTCVideoRenderer*)createWithTextureRegistry:(id<FlutterTextureRegistry>)registry
                                            messenger:(NSObject<FlutterBinaryMessenger>*)messenger;

- (void)rendererSetSrcObject:(FlutterRTCVideoRenderer*)renderer stream:(RTCVideoTrack*)videoTrack;

@end
