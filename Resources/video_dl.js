var VideoDL = {};
var Tifs = {fs: Titanium.Filesystem};

VideoDL.init = function()
{
	this.db = Titanium.Database.open("videodb");

	this.contentArea = $('#content');

	// Load all the topics
	VideoDL.loadVideos();

}

VideoDL.loadVideos = function()
{
	this.videos = [];

	var vidapp = this;
	
	var xhr = Titanium.Network.createHTTPClient();
	xhr.onload = function() {
		var vidjson = JSON.parse(this.responseData);
		for (var i=0; i < vidjson.length; i++) {
			if (vidjson[i].disabled === false) {
				$('#ytid').append(VideoDL.Video(vidjson[i].youtube_id));
			};
		};
		
    };
	xhr.open("GET", "http://freefallhighscore.heroku.com/videos.json");
	xhr.send();
	
	/*topicDir.getDirectoryListing().forEach(function(videoFile)
	{
		var video = new VideoDL.Video(videoFile);
		vidapp.contentArea.append(video.contentDiv);
		vidapp.videos.push(topic);
	});*/

	//this.currentVideo = this.videos[0];
	//this.currentVideo.show();
}


VideoDL.Video = function(youtube_id)
{
	// Load topic content text
	this.contentDiv = $('<div class="video_content" id="yt_'+ youtube_id +'">');
	this.ytIframe = $('<iframe width="540" height="333" frameborder="0">');
	this.ytIframe.attr('src','http://www.youtube.com/embed/' + youtube_id + '?version=3&loop=1&autoplay=1&theme=dark&autohide=2&controls=0&modestbranding=1');
	//this.ytIframe.attr('src','http://www.youtube.com/embed/' + youtube_id);
	this.contentDiv.append(this.ytIframe);
	//this.contentDiv.hide();
	
	return this.contentDiv;

}

VideoDL.Video.prototype.show = function()
{
	this.contentDiv.show();
}

VideoDL.Video.prototype.hide = function()
{
	this.contentDiv.hide();
}

$(document).ready(function()
{
	VideoDL.init();
});
