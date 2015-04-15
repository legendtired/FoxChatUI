#
#  FoxChatUI.framework
#  foxchat.im
#

Pod::Spec.new do |s|

  s.name         = "FoxChatUI"
  s.version      = "0.0.3"
  s.summary      = "FoxChat SDK UI版本"
  s.homepage     = "http://foxchat.im"
  s.screenshots  = "http://foxchat.im/img/doc/sc1.png", "http://foxchat.im/img/doc/sc2.png", "http://foxchat.im/img/doc/sc3.png"

  s.license      = {
    :type => 'Copyright',
    :text => 'Copyright (c) 2015 FoxChat.im. All rights reserved.'
  }

  s.author       = { "legend" => "legendsky@hotmail.com" }
  s.platform     = :ios, "6.0"
  
  s.source       = { :git => "https://github.com/legendtired/FoxChatUI.git", :tag => s.version }
  
  s.vendored_frameworks = 'FoxChatUI.framework'
  s.resource = 'FoxChatUI.bundle'
  
  s.frameworks = "AVFoundation", "MapKit", "AudioToolbox"
  s.libraries = "z", "sqlite3.0"
  
  s.requires_arc = true

end
